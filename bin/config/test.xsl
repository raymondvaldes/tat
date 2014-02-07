<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="2.0">

<xsl:output omit-xml-declaration="yes" method="html"/>
<xsl:strip-space elements="*"/>

<xsl:template match="Document">
    <html>
     <head><title>Test</title></head>
        <xsl:apply-templates/>
    </html>
</xsl:template>

<xsl:template match="Page">
    <body>
        <xsl:apply-templates/><hr/>
        Page:<xsl:value-of select="@pageNumber"/>
    </body>
</xsl:template>

<xsl:template match="Chunk">
    <xsl:value-of select="."/><br/>
</xsl:template>

<xsl:template match="*">
<xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>
